#include <string>
#include "Issue.h"

std::string Issue::getStatus() {
  switch (status) {
    case New:
      return "New";
    case Assigned:
      return "Assigned";
    case WontFix:
      return "WontFix";
  }
  return "?";
}

std::string Issue::getPriority() {
  switch (priority) {
    case Low:
      return "Low";
    case Medium:
      return "Medium";
    case High:
      return "High";
    case Top:
      return "Top";
  }
  return "?";
}
