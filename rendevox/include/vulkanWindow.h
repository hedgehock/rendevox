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
    uint32_t formatsCount;
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

void vulkanWindowCreateSurface();

void vulkanWindowPickPhysicalDevice();

void vulkanWindowCreateLogicalDevice();

void vulkanWindowCreateSwapChain();

// Vulkan Pick Physical Device Functions
bool vulkanWindowIsDeviceSuitable(VkPhysicalDevice device);

vulkanWindowQueueFamilyIndices vulkanWindowFindQueueFamilies(VkPhysicalDevice device);

bool vulkanWindowCheckDeviceExtensionSupport(VkPhysicalDevice device);

// Vulkan Create Swap Chain functions
vulkanWindowSwapChainSupportDetails vulkanWindowQuerySwapChainSupport(VkPhysicalDevice device);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR* availableFormats, uint32_t formatsCount);

VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR* availablePresentModes, uint32_t presentModeCount);

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities);

// Vulkan print error and exit
void vulkanError(vulkanString errorMessage);