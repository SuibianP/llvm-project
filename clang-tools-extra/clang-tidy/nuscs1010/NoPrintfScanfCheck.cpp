//===--- NoPrintfScanfCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoPrintfScanfCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoPrintfScanfCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource,
               callExpr(callee(cxxMethodDecl(
                                   anyOf(hasName("printf"), hasName("scanf")))
                                   .bind("decl")))
                   .bind("io")),
      this);
}

void NoPrintfScanfCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("io");
  const auto *MatchedDecl = Result.Nodes.getNodeAs<CXXMethodDecl>("decl");
  diag(MatchedCall->getBeginLoc(), "use of %0 is discouraged")
      << MatchedDecl->getDeclName() << MatchedCall->getSourceRange();
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
