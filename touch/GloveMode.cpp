/*
 * Copyright (C) 2021-2022 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "GloveModeService"

#include "GloveMode.h"

#include <android-base/properties.h>
#include <android-base/strings.h>
#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

const std::string kGloveModePath = pathFinder();

Return<bool> GloveMode::isEnabled() {
    std::ifstream file(kGloveModePath);
    bool enabled;

    file >> enabled;

    return enabled;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(kGloveModePath);

    file << enabled << std::flush;

    return !file.fail();
}

Return<std::string> GloveMode::pathFinder() {
    std::string deviceName = (android::base::GetProperty("ro.product.device", "");
    std::string result;

    switch(deviceName) {
        case "akatsuki":
            result = "/sys/devices/virtual/input/lge_touch/glove_mode";
            break;
        case "akari":
            if ((android::base::GetProperty("sys.touch_id", "") == "3") {
                result = "/sys/devices/virtual/input/clearpad/glove";
            else
                result = "/sys/bus/platform/devices/synaptics_tcm.0/synaptics_tcm/dynamic_config/glove";
            }
            break;
        case "apollo":
                result = "/sys/devices/common_touch/touch/glove_mode";
            break;
        case default:
                result = NULL;
            break;
    }
    return result;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
