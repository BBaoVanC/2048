project(
  '2048', 'cpp',
  version: '0.1',
  default_options: [
    'warning_level=3',
    'cpp_std=c++23'
  ],
)

include = include_directories('include')
srcs = [
  'src/main.cpp',
  'src/display.cpp',
  'src/game.cpp',
]

ncurses_dep = dependency('ncurses')

exe = executable(
  '2048', srcs,
  include_directories: include,
  dependencies: [ncurses_dep],
  install: true
)
