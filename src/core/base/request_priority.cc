// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "core/base/request_priority.h"

namespace tit {
namespace net {

const char* RequestPriorityToString(RequestPriority priority) {
  switch (priority) {
    case THROTTLED:
      return "THROTTLED";
    case IDLE:
      return "IDLE";
    case LOWEST:
      return "LOWEST";
    case LOW:
      return "LOW";
    case MEDIUM:
      return "MEDIUM";
    case HIGHEST:
      return "HIGHEST";
  }
  return "UNKNOWN_PRIORITY";
}

}  // namespace net
}  // namespace tit