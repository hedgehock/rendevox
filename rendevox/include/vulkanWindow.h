typedef struct {
    bool GraphicsFamilyPresent;
    bool PresentFamilyPresent;
} vulkanWindowIs;

typedef struct {
    uint32_t GraphicsFamily;
    uint32_t PresentFamily;
} vulkanWindowFamily;

typedef struct {
    vulkanWindowIs is;
    vulkanWindowFamily family;
} vulkanWindowQueueFamilyIndices;

typedef struct {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR* formats;
    VkPresentModeKHR* presentModes;
    uint32_t formatCount;
    uint32_t presentModeCount;
} vulkanWindowSwapChainSupportDetails;

typedef char* vulkanString;


// Vulkan
void vulkanWindowRunVulkanApp(window window);

// Vulkan main functions
void vulkanWindowCreateWindow(window window);

void vulkanWindowInit();

void vulkanWindowMainLoop();

void vulkanWindowCleanup();

// Vulkan initialisation functions
void vulkanWindowCreateInstance();

void vulkanWindowPickPhysicalDevice();

// Vulkan Pick Physical Device Functions
bool vulkanWindowIsDeviceSuitable(VkPhysicalDevice device);

vulkanWindowQueueFamilyIndices vulkanWindowFindQueueFamilies(VkPhysicalDevice device);

void vulkanWindowCreateLogicalDevice();

void vulkanWindowCreateSurface();

bool vulkanWindowCheckDeviceExtensionSupport(VkPhysicalDevice device);

vulkanWindowSwapChainSupportDetails vulkanWindowQuerySwapChainSupport(VkPhysicalDevice device);

// Vulkan print error and exit
void vulkanError(vulkanString errorMessage);