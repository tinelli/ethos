#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H

#include <map>
#include <set>
#include "expr.h"

namespace alfc {

class State;

using Ctx = std::map<Expr, Expr>;
std::ostream& operator<<(std::ostream& out, const Ctx& c);
/** 
 * Expression class
 */
class TypeChecker
{
 public:
  TypeChecker(State& s);
  ~TypeChecker();
  /** Return its type */
  const Expr& getType(Expr& e, std::ostream* out = nullptr);
  /** Set type rule for literal */
  void setTypeRule(Kind k, const Expr& t);
  /** Define program */
  void defineProgram(const Expr& v, const Expr& prog);
  /** Has program */
  bool hasProgram(const Expr& v) const;
  /** Maybe evaluate */
  Expr evaluateProgram(const std::vector<Expr>& args, Ctx& newCtx);
  /** */
  bool match(const Expr& a, const Expr& b, Ctx& ctx, std::set<std::pair<Expr, Expr>>& visited);
  bool match(const Expr& a, const Expr& b, Ctx& ctx);
  /**
   * Clone this expression, which creates a deep copy of this expression and
   * returns it. The dag structure of pn is the same as that in the returned
   * expression.
   *
   * @return the cloned expression.
   */
  Expr evaluate(Expr& e, Ctx& ctx);
  Expr evaluate(Expr& e);
 private:
  /** Compiled version */
  Expr run_getTypeInternal(Expr& hdType, const std::vector<Expr>& args, std::ostream* out);
  /** Return its type */
  Expr getTypeInternal(Expr& e, std::ostream* out);
  /** Compiled version */
  Expr run_evaluate(Expr& e, Ctx& ctx);
  /** Compiled version */
  Expr run_evaluateProgram(const std::vector<Expr>& args, Ctx& ctx);
  /** The state */
  State& d_state;
  /** The builtin literal kinds */
  std::set<Kind> d_literalKinds;
  /** Mapping literal kinds to type rules */
  std::map<Kind, Expr> d_literalTypeRules;
  /** Programs */
  std::map<Expr, Expr> d_programs;
};

}  // namespace alfc

#endif 
