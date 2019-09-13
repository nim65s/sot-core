/*
 * Copyright 2010,
 * Florent Lamiraux
 *
 * CNRS
 *
 */

#ifndef CONSTRAINT_COMMAND_H
#define CONSTRAINT_COMMAND_H

#include <boost/assign/list_of.hpp>

#include <dynamic-graph/command-getter.h>
#include <dynamic-graph/command-setter.h>
#include <dynamic-graph/command.h>

namespace dynamicgraph {
namespace sot {
namespace command {
namespace constraint {
using ::dynamicgraph::command::Command;
using ::dynamicgraph::command::Value;

// Command AddJacobian
class AddJacobian : public Command {
 public:
  virtual ~AddJacobian() {}
  /// Create command and store it in Entity
  /// \param entity instance of Entity owning this command
  /// \param docstring documentation of the command
  AddJacobian(Constraint& entity, const std::string& docstring)
      : Command(entity, boost::assign::list_of(Value::STRING), docstring) {}
  virtual Value doExecute() {
    Constraint& constraint = static_cast<Constraint&>(owner());
    std::vector<Value> values = getParameterValues();
    std::string signalName = values[0].value();
    std::istringstream iss(signalName);
    SignalBase<int>& signal =
        dynamicgraph::PoolStorage::getInstance()->getSignal(iss);
    try {
      Signal<dynamicgraph::Matrix, int>& matrixSignal =
          dynamic_cast<Signal<dynamicgraph::Matrix, int>&>(signal);
      constraint.addJacobian(matrixSignal);
    } catch (const std::bad_cast& exc) {
      std::string msg(signalName + " is not of type matrix.");
      SOT_THROW ExceptionSignal(ExceptionSignal::BAD_CAST, msg);
    }
    // return void
    return Value();
  }
};  // class AddJacobian
}  // namespace constraint
}  // namespace command
}  // namespace sot
}  // namespace dynamicgraph

#endif  // CONSTRAINT_COMMAND_H
