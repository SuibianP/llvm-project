//===--- NoStaticStorageVariablesCheck.cpp - clang-tidy
//--------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

/*
 * This is not a duplicate of cppcoreguidelines-avoid-non-const-global-variables
 * const global variables in C are also banned as they are neither guaranteed
 * compile time nor static linkage
 */

#include "NoStaticStorageVariablesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void NoStaticStorageVariablesCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource,
               varDecl(hasStaticStorageDuration()).bind("static")),
      this);
}

void NoStaticStorageVariablesCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("static");
  diag(MatchedDecl->getLocation(), "global or static variable declared",
       DiagnosticIDs::Error);
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
