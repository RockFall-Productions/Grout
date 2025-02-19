# Tive que rodar no Linux:
#sudo apt install pkgconf
#sudo apt install libx11-dev libxkbcommon-x11-dev libx11-xcb-dev libxft-dev
#sudo apt install autoconf
#sudo apt install libtool
#sudo apt install bison
#sudo apt install gperf
#sudo apt install libgles2-mesa-dev
#sudo apt install libxext-dev
#sudo apt install libxrandr-dev
#sudo apt install libxi-dev
#sudo apt install libxcursor-dev
#sudo apt install libxdamage-dev
#sudo apt install libxinerama-dev
#sudo apt install libsdl2-dev
#sudo apt install libfmt-dev
#sudo apt install catch2
#sudo apt install mingw-w64-tools


# Windows
# pacman -S pkg-config
# pacman -S mingw-w64-ucrt-x86_64-fmt

# Pra compilar:
# meson setup --cross-file crossfile.txt build-mingw
# meson compile -C builddir

# HACK: Tive que fazer mudanças no ImGuizmo para atualizar funções depreciadas: avalaiar a versão correta


#https://chatgpt.com/c/6771db3c-78a0-800f-8ce9-90bf06967ce5



# Meson Build File for the Grout Project

project('Grout',  ['c', 'cpp'],
  version : '1.0',
  license : [ 'proprietary'],
  default_options: [
        'warning_level=0', 
        'buildtype=debugoptimized',
        'cpp_std=c++17',
        ],
    )

outputdir = 'bin/' + get_option('buildtype') + '-' + host_machine.system() + '-' + host_machine.cpu_family()

inc = []
subdir('Grout/third-part')

glfw = subproject('glfw')
glm = subproject('glm')
imgui = subproject('imgui-docking')
#imguizmo = subproject('imguizmo')
spdlog = subproject('spdlog')

bin_dep_libs = [
  glad,
  assimp
]

# Declare source files for each module

# Core module
core_sources = files(
  'Grout/src/Grout/Core/Application.cpp',
  'Grout/src/Grout/Core/Layer.cpp',
  'Grout/src/Grout/Core/LayerStack.cpp',
  'Grout/src/Grout/Core/Log.cpp',
  'Grout/src/Grout/Core/Timestep.cpp',
  #'Grout/src/Grout/Core/Window.cpp',
  #'Grout/src/Grout.cpp'
)
inc += include_directories('Grout/src/Grout/Core')
inc += include_directories('Grout/src')

imgui_layer = files(
  'Grout/src/Grout/ImGui/ImGuiLayer.cpp',
  'Grout/src/Grout/ImGui/ImGuiBuild.cpp'
)
inc += include_directories('Grout/src/Grout/ImGui')


# Renderer module
renderer_sources = files(
  'Grout/src/Grout/Renderer/Buffer.cpp',
  'Grout/src/Grout/Renderer/Camera.cpp',
  'Grout/src/Grout/Renderer/Mesh.cpp',
  'Grout/src/Grout/Renderer/Shader.cpp',
  'Grout/src/Grout/Renderer/Renderer.cpp',
  'Grout/src/Grout/Renderer/RendererAPI.cpp',
  'Grout/src/Grout/Renderer/Texture.cpp',
  'Grout/src/Grout/Renderer/VertexArray.cpp',
  'Grout/src/Grout/Renderer/RenderCommand.cpp'
)
inc += include_directories('Grout/src/Grout/Renderer')

# Scene module
scene_sources = files(
  'Grout/src/Grout/Scene/Object.cpp',
  'Grout/src/Grout/Scene/Transform.cpp'
)
inc += include_directories('Grout/src/Grout/Scene')

# Third-party dependencies sources
third_party_sources = files(
  'Grout/third-part/stb/stb_image.cpp',
  #'Grout/third-part/glm/glm/glm.hpp',
  #'Grout/third-part/glm/glm/glm.inl'
)

# Plataform
plataform_sources = files(
  'Grout/src/Plataform/OpenGL/OpenGLBuffer.cpp',
  'Grout/src/Plataform/OpenGL/OpenGLContext.cpp',
  'Grout/src/Plataform/OpenGL/OpenGLRendererAPI.cpp',
  'Grout/src/Plataform/OpenGL/OpenGLShader.cpp',
  'Grout/src/Plataform/OpenGL/OpenGLTexture.cpp',
  'Grout/src/Plataform/OpenGL/OpenGLVertexArray.cpp',
  #'Grout/src/Plataform/OpenGL/OpenGLVertexBuffer.cpp',
  #'Grout/src/Plataform/OpenGL/OpenGLIndexBuffer.cpp',
  #'Grout/src/Plataform/OpenGL/OpenGLRenderCommand.cpp',

  'Grout/src/Plataform/Windows/WindowsWindow.cpp',
  'Grout/src/Plataform/Windows/WindowsInput.cpp',
)
inc += include_directories('Grout/src/Plataform/OpenGL')
inc += include_directories('Grout/src/Plataform/Windows')

# Combine all sources for Grout
grout_sources = core_sources + scene_sources + renderer_sources + third_party_sources + imgui_layer + plataform_sources

# Declare header files for each module

# Core module headers
#core_headers = files(
#  'Grout/src/Core/Application.h',
#  'Grout/src/Core/Layer.h',
#  'Grout/src/Core/Log.h',
#  'Grout/src/Core/Timestep.h',
#  'Grout/src/Core/Window.h',
#  'Grout/src/Grout.h'
#)


# Scene module headers
#scene_headers = files(
#  'Grout/src/Scene/Object.h',
#  'Grout/src/Scene/Transform.h'
#)


# Renderer module headers
#renderer_headers = files(
#  'Grout/src/Renderer/Buffer.h',
#  'Grout/src/Renderer/Camera.h',
#  'Grout/src/Renderer/Shader.h',
#  'Grout/src/Renderer/Renderer.h',
#  'Grout/src/Renderer/Texture.h',
#  'Grout/src/Renderer/VertexArray.h',
#  'Grout/src/Renderer/RenderCommand.h'
#)


# Third-party dependencies headers
#third_party_headers = files(
#  'Grout/third-part/stb/stb_image.h',
#  'Grout/third-part/glm/glm/glm.hpp',
#  'Grout/third-part/glm/glm/glm.inl'
#)
inc += include_directories('Grout/third-part/stb')


deps = [
  glfw.get_variable('glfw_dep'),
  glm.get_variable('glm_dep'),
  imgui.get_variable('imgui_dep'),
  #imguizmo.get_variable('imguizmo_dep'),
  spdlog.get_variable('spdlog_dep'),
]


cpp_args_sandbox = [
    '-D_CRT_SECURE_NO_WARNINGS',
    '-DGLM_ENABLE_EXPERIMENTAL',
    '-DIMGUI_DEFINE_MATH_OPERATORS',
    '-DGRT_DEBUG',
    '-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM'
    #'-DSPDLOG_WCHAR_TO_UTF8_SUPPORT',
    #'-fpermissive',
    ]

# System specific settings
if host_machine.system() == 'windows'
  cpp_args_sandbox += ['-DGRT_BUILD_DLL', '-DGLFW_INCLUDE_NONE']
endif

# Main Grout library
grout = static_library('grout', grout_sources,
  include_directories : inc,
  dependencies : deps,

  cpp_args : cpp_args_sandbox,
  #cpp_pch : 'Grout/src/grtpch.h',
  link_with : bin_dep_libs,
  install : true
)

# Precompiled header
#pch_header = 'Grout/grtpch.h'
#pch_source = 'Grout/src/grtpch.cpp'
#pch = precompiled_header(pch_header, pch_source)

# Sandbox executable
sandbox_sources = files(
  'Sandbox/src/SandboxApp.cpp',
  'Sandbox/src/BoidWorldLayer.cpp',
  'Sandbox/src/Boids.cpp',
  'Sandbox/src/Spawner.cpp',
  'Sandbox/src/World.cpp',
  'Sandbox/src/Flock.cpp',
  'Sandbox/src/Spawner.h',
  'Sandbox/src/World.h',
  'Sandbox/src/Flock.h',
  'Sandbox/src/BoidWorldLayer.h',
  'Sandbox/src/Boids.h'
)

inc += include_directories('Sandbox/src')


sandbox = executable('sandbox', sandbox_sources,
  include_directories : inc,
  #dependencies : [grout],
  link_with : [grout],
  dependencies: deps,
  install : true,
  cpp_args : cpp_args_sandbox
)

#test_sources = files(
#  'Test/src/Hello.cpp'
#)
#
#sandbox = executable('test_app', test_sources,
#  include_directories : inc,
#  #dependencies : [grout],
#  link_with : [grout],
#  dependencies: deps,
#  install : true,
#  cpp_args : cpp_args_sandbox
#)

# Installation configuration
#install_data('Grout/grout_logo.svg', install_dir : 'share/grout/')
