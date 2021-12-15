set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyNUSCS1010Module
  ForbiddenTypesCheck.cpp
  NUSCS1010TidyModule.cpp
  NoBreakCheck.cpp
  NoContinueCheck.cpp
  NoGotoCheck.cpp
  NoIncrDecrOperatorsCheck.cpp
  NoNestedTernaryOperatorCheck.cpp
  NoPrintfScanfCheck.cpp
  NoSwitchCheck.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils

  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyNUSCS1010Module
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTooling
  )
