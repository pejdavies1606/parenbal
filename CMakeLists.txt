cmake_minimum_required(VERSION 3.0)

set(project_name "parenbal")
project(${project_name})

set(project_src
   "src/parenbal.c"
   "src/main.c"
)

add_executable(${project_name}
   ${project_src}
)

target_include_directories(${project_name}
   PUBLIC "include/"
)
