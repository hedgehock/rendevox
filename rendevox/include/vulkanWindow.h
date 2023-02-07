typedef struct {
    bool GraphicsFamilyPresent;
    bool PresentFamilyPresent;
} vulkanIs;

typedef struct {
    uint32_t GraphicsFamily;
    uint32_t PresentFamily;
} vulkanFamily;

typedef struct {
    vulkanIs is;
    vulkanFamily family;
} vulkanQueueFamilyIndices;

typedef struct {
    VkSurfaceCapabilitiesKHR capabilities;
    VkSurfaceFormatKHR* formats;
    VkPresentModeKHR* presentModes;
    uint32_t formatCount;
    uint32_t presentModeCount;
} vulkanSwapChainSupportDetails;

typedef char* string;


// Vulkan
void runVulkanApp(window window);

// Vulkan main functions
void vulkanCreateWindow(window window);

void vulkanInit();

void vulkanMainLoop();

void vulkanCleanup();

// Vulkan initialisation functions
void vulkanCreateInstance();

void vulkanPickPhysicalDevice();

// Vulkan Pick Physical Device Functions
bool isDeviceSuitable(VkPhysicalDevice device);

vulkanQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

void vulkanCreateLogicalDevice();

void vulkanCreateSurface();

bool vulkanCheckDeviceExtensionSupport(VkPhysicalDevice device);

vulkanSwapChainSupportDetails vulkanQuerySwapChainSupport(VkPhysicalDevice device);

// Vulkan print error and exit
void vulkanError(string errorMessage);