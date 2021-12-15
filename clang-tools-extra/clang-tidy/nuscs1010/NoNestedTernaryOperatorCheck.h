//===--- NoNestedTernaryOperatorCheck.h - clang-tidy ------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_NUSCS1010_NONESTEDTERNARYOPERATORCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_NUSCS1010_NONESTEDTERNARYOPERATORCHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace nuscs1010 {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/nuscs1010-no-nested-ternary-operator.html
class NoNestedTernaryOperatorCheck : public ClangTidyCheck {
public:
  NoNestedTernaryOperatorCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace nuscs1010
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_NUSCS1010_NONESTEDTERNARYOPERATORCHECK_H
