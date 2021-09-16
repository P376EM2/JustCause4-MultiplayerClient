load("@bazel_tools//tools/cpp:toolchain_utils.bzl", "find_cpp_toolchain")
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "C_COMPILE_ACTION_NAME")

CompilationAspect = provider()

def _get_project_info(target, ctx):
  cc = target[CcInfo]
  cc_toolchain = find_cpp_toolchain(ctx)
  feature_configuration = cc_common.configure_features(
    ctx = ctx,
    cc_toolchain = cc_toolchain,
    requested_features = ctx.features,
    unsupported_features = ctx.disabled_features,
  )
  compile_variables = cc_common.create_compile_variables(
    feature_configuration = feature_configuration,
    cc_toolchain = cc_toolchain,
    user_compile_flags = ctx.fragments.cpp.copts,
  )
  compiler_options = cc_common.get_memory_inefficient_command_line(
    feature_configuration = feature_configuration,
    action_name = C_COMPILE_ACTION_NAME,
    variables = compile_variables,
  )
  if cc:
    cc_info = struct(
      include_dirs        = cc.compilation_context.includes.to_list(),
      system_include_dirs = cc.compilation_context.system_includes.to_list(),
      quote_include_dirs  = cc.compilation_context.quote_includes.to_list(),
      compile_flags       = compiler_options + (ctx.rule.attr.copts if "copts" in dir(ctx.rule.attr) else []) + ctx.fragments.cpp.cxxopts + ctx.fragments.cpp.copts,
      defines             = cc.compilation_context.defines.to_list(),
    )
  else:
    cc_info = None
  return struct(
      build_file_path = ctx.build_file_path,
      workspace_root  = ctx.label.workspace_root,
      package         = ctx.label.package,

      files = struct(**{name: _get_file_group(ctx.rule.attr, name) for name in ['srcs', 'hdrs']}),
      deps  = [str(dep.label) for dep in getattr(ctx.rule.attr, 'deps', [])],
      target = struct(label=str(target.label), files=[f.path for f in target.files.to_list()]),
      kind = ctx.rule.kind,

      cc = cc_info,
  )

def _get_file_group(rule_attrs, attr_name):
  file_targets = getattr(rule_attrs, attr_name, None)
  if not file_targets: return []
  return [file.path for t in file_targets for file in t.files.to_list()]

def _msbuild_aspect_impl(target, ctx):
  info_file = ctx.actions.declare_file(target.label.name + '.msbuild')
  content = _get_project_info(target, ctx).to_json()
  ctx.actions.write(info_file, content, is_executable=False)

  outputs = depset([info_file]).to_list()
  for dep in getattr(ctx.rule.attr, 'deps', []):
    outputs += dep[OutputGroupInfo].msbuild_outputs.to_list()
  return [OutputGroupInfo(msbuild_outputs=outputs)]

msbuild_aspect = aspect(
    attr_aspects = ["deps"],
     attrs = {
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
    },
    fragments    = ["cpp"],
    required_aspect_providers = [CompilationAspect],
    implementation = _msbuild_aspect_impl,
)
