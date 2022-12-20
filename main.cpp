#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#include "level-zero/include/ze_api.h"
#include "level-zero/samples/include/zello_log.h"

int main() {
    ze_result_t result;

    // Initialize the driver
    if((result = zeInit(0)) != ZE_RESULT_SUCCESS) {
        cout << "zeInit: " << to_string(result) << endl;
        return 1;
    }
    cout << "Driver initialized." << endl;

    // Discover all the driver instances
    uint32_t driverCount = 0;
    if ((result = zeDriverGet(&driverCount, nullptr)) != ZE_RESULT_SUCCESS) {
        cout << "zeDriverGet: " << to_string(result) << endl;
        return 1;
    }

    ze_driver_handle_t* allDrivers = new ze_driver_handle_t[driverCount];
    if ((result = zeDriverGet(&driverCount, allDrivers)) != ZE_RESULT_SUCCESS) {
        cout << "zeDriverGet: " << to_string(result) << endl;
        return 1;
    }

    // Find a driver instance with a GPU device
    ze_driver_handle_t hDriver = nullptr;
    ze_device_handle_t hDevice = nullptr;
    for(int i = 0; i < driverCount; ++i) {
        uint32_t deviceCount = 0;
        if ((result = zeDeviceGet(allDrivers[i], &deviceCount, nullptr)) != ZE_RESULT_SUCCESS) {
            cout << "zeDeviceGet: " << to_string(result) << endl;
            return 1;
        }

        ze_device_handle_t* allDevices = new ze_device_handle_t[deviceCount];
        if ((result = zeDeviceGet(allDrivers[i], &deviceCount, allDevices)) != ZE_RESULT_SUCCESS) {
            cout << "zeDeviceGet: " << to_string(result) << endl;
            return 1;
        }

        for(int d = 0; d < deviceCount; ++d) {
            ze_device_properties_t device_properties;
            if ((result = zeDeviceGetProperties(allDevices[d], &device_properties)) != ZE_RESULT_SUCCESS) {
                cout << "zeDeviceGetProperties: " << to_string(result) << endl;
                return 1;
            }

            if(ZE_DEVICE_TYPE_GPU == device_properties.type) {
                hDriver = allDrivers[i];
                hDevice = allDevices[d];

                cout << "Found device: " << device_properties.name << endl;

                uint32_t num_groups;
                zeDeviceGetCommandQueueGroupProperties(hDevice, &num_groups, nullptr);
                vector<ze_command_queue_group_properties_t> properties(num_groups);
                memset(properties.data(), 0, sizeof(ze_command_queue_group_properties_t) * num_groups);
                for (auto &properties_item : properties) {
                    properties_item.stype = ZE_STRUCTURE_TYPE_COMMAND_QUEUE_GROUP_PROPERTIES;
                }
                zeDeviceGetCommandQueueGroupProperties(hDevice, &num_groups, properties.data());
                for(int i; i < properties.size(); i++) {
                    if (properties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COMPUTE) {
                        cout << "Found " << properties[i].numQueues << " compute engines in command queue group ordinal " << i << endl;
                    }
                    if (properties[i].flags & ZE_COMMAND_QUEUE_GROUP_PROPERTY_FLAG_COPY) {
                        cout << "Found " << properties[i].numQueues << " copy engines in command queue group ordinal " << i << endl;
                    }
                }
            }
        }

        free(allDevices);
        if(nullptr != hDriver) {
            break;
        }
    }

    free(allDrivers);
    if(nullptr == hDevice) {
        cout << "No GPU devices found" << endl;
        return 1;
    }
}
