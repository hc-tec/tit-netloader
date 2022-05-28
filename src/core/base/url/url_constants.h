//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_CONSTANTS_H
#define TIT_NETLOADER_URL_CONSTANTS_H

#include <co/def.h>

namespace tit {
namespace net {

extern const char kAboutBlankURL[];
extern const char16_t kAboutBlankURL16[];
extern const char kAboutSrcdocURL[];
extern const char16_t kAboutSrcdocURL16[];

extern const char kAboutBlankPath[];
extern const char16_t kAboutBlankPath16[];
extern const char kAboutSrcdocPath[];
extern const char16_t kAboutSrcdocPath16[];

extern const char kAboutScheme[];
extern const char16_t kAboutScheme16[];
extern const char kBlobScheme[];
extern const char16_t kBlobScheme16[];
// The content scheme is specific to Android for identifying a stored file.
extern const char kContentScheme[];
extern const char16_t kContentScheme16[];
extern const char kContentIDScheme[];
extern const char16_t kContentIDScheme16[];
extern const char kDataScheme[];
extern const char16_t kDataScheme16[];
extern const char kFileScheme[];
extern const char16_t kFileScheme16[];
extern const char kFileSystemScheme[];
extern const char16_t kFileSystemScheme16[];
extern const char kFtpScheme[];
extern const char16_t kFtpScheme16[];
extern const char kHttpScheme[];
extern const char16_t kHttpScheme16[];
extern const char kHttpsScheme[];
extern const char16_t kHttpsScheme16[];
extern const char kJavaScriptScheme[];
extern const char16_t kJavaScriptScheme16[];
extern const char kMailToScheme[];
extern const char16_t kMailToScheme16[];
extern const char kQuicTransportScheme[];
extern const char16_t kQuicTransportScheme16[];
extern const char kTelScheme[];
extern const char16_t kTelScheme16[];
extern const char kUrnScheme[];
extern const char16_t kUrnScheme16[];
extern const char kUuidInPackageScheme[];
extern const char16_t kUuidInPackageScheme16[];
extern const char kWsScheme[];
extern const char16_t kWsScheme16[];
extern const char kWssScheme[];
extern const char16_t kWssScheme16[];

// Used to separate a standard scheme and the hostname: "://".
extern const char kStandardSchemeSeparator[];
extern const char16_t kStandardSchemeSeparator16[];

extern const size_t kMaxURLChars;

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_CONSTANTS_H
