//===--- ForbiddenTypesCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForbiddenTypesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace nuscs1010 {

void ForbiddenTypesCheck::registerMatchers(MatchFinder *Finder) {
  /* TODO we can have a compile time mechanism to expand a container to
   * parameter list, essentially building a asAnyString using things like
   * std::forward Then we can have a map to corresponding suggested types
   */
  Finder->addMatcher(
      traverse(
          TK_IgnoreUnlessSpelledInSource,
          typeLoc(unless(hasAncestor(functionDecl(isMain()))),
                  loc(hasCanonicalType(anyOf(asString("int"), asString("float"),
                                             asString("short")))))
              .bind("x")),
      this);
  Finder->addMatcher(
      traverse(TK_IgnoreUnlessSpelledInSource,
               functionDecl(isMain(),
                            hasBody(hasDescendant(typeLoc(
                                loc(hasCanonicalType(anyOf(asString("int"),
                                                           asString("float"),
                                                           asString("short"))))
                                    .bind("x")))))),
      this);
  // TODO There has to be a more elegant way to do this, maybe clearer about
  // TypeLoc in AST
  // TODO the documentation of TypeLoc can be improved on how nested ones work
  // since they are not included in the AST by default
}

void ForbiddenTypesCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<TypeLoc>("x");
  diag(MatchedDecl->getBeginLoc(), "banned type %0 used", DiagnosticIDs::Error)
      << MatchedDecl->getType().getAsString() << MatchedDecl->getSourceRange();
  // TODO add fixit to suggested type
  // why the behaviour of CanQual and QualType and Type are so weird?
}

} // namespace nuscs1010
} // namespace tidy
} // namespace clang
