#project('Glad', 'c', 
#  default_options: [
#    'buildtype=debugoptimized',  # Ajuste o tipo de build conforme necessário
#    'warning_level=3',
#    'debug=false'
#  ])

glad_sources = files(
  'src/glad.c'
)

glad_headers = files(
  'include/glad/glad.h',
  'include/KHR/khrplatform.h'
)

inc += include_directories('include')

glad = static_library('glad', glad_sources,
  include_directories: inc,
  pic: true  # Ativa o compilação PIC (Position Independent Code) em sistemas Linux
)



# Configuração de diretório de saída
#executable('glad-bin', glad_sources,
#  install: true,
#  link_with: glad,
#  default_library: 'static',
#  target_dir: 'bin/${buildtype}/glad'
#)
#
## Configurações de debug e release
#if get_option('buildtype') == 'debug'
#  add_project_arguments('-g', language: 'c')
#  add_project_arguments('-DDEBUG', language: 'c')
#elif get_option('buildtype') == 'release'
#  add_project_arguments('-O3', language: 'c')
#  add_project_arguments('-DNDEBUG', language: 'c')
#endif
#
## Configurações específicas para sistemas
#if host_machine.system() == 'windows'
#  add_project_arguments('/std:c11', language: 'c')
#  add_project_link_arguments('/LTCG', language: 'c')
#elif host_machine.system() == 'linux'
#  add_project_arguments('-fPIC', language: 'c')  # PIC ativado em sistemas Linux
#endif
