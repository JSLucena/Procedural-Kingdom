# Vulkan Initialization Functions

### Concepts

#### VKInstace
Store application state

#### Surface
Where we are placing drawings(e.g window)

#### Device
Interface to physical Device

#### Swapchain
A queue of images to be presented on the screen

#### Imageview
Image lenses?

#### Render-pass
general description of steps Your drawing commands are divided into and of resources used during rendering. We can't render anything in Vulkan without a render pass. And each render pass must have one or more steps.

#### Sub-passes
(sub)collection of resources defined for the render-pass. Render-pass's resources may include render-targets (color, depth/stencil, resolve) and input data (resources that, potentially, were render-targets in previous sub-passes of the same render-pass). And these resources are called,

#### Attachments
Resources for render-passes

#### Graphics Pipeline
Encompasses the configuration of the GPU for the draw.
It is the sequence of operations that take the vertices and textures of your meshes all the way to the pixels in the render targets. 

#### Frame Buffers
Binds an image to an attachment

#### Command Pool
Command pools are opaque objects that command buffer memory is allocated from, and which allow the implementation to amortize the cost of resource creation across multiple command buffers. Command pools are externally synchronized, meaning that a command pool must not be used concurrently in multiple threads. 

#### Command Buffer
Object used to record commands to be submitted to the device


## CreateInstance
- Define application Info (name, version, API version)
- Gets the required extensions
- Specifies debug messenger
- Stored into ***instance***

## SetupDebugMessenger
- Uses **instance**
- Sets up Debug messenger
- Stores into ***debugMessenger***

## CreateSurface
- Uses **instance** ; **window**
- GLFW support for Vulkan
- Stores into ***surface***

## PickPhysicalDevice
- Uses **instance**
- Rates all devices using a point system
- Stores the best candidate into ***physicalDevice*** if suitable

## CreateLogicalDevice
- Uses **physicalDevice**
- Finds queue families for requested device
- Checks if graphics and surface presentation is supported
- Defines Queue Info, connects enabled features (e.g wideLines, largePoints)
- Stores into ***device*** and gets both queues

## CreateSwapChain
- Uses **physicalDevice** ; **surface** ; **queues** ; **device**
- Checks swapchain support
- Define and create swapchain
- Stores into ***swapChain***
- Resize it to fit our surface

## CreateImageViews
- Uses **device**; **swapChainImages**
- Define and create one image View for each swap chain image( e.g specify color components, view type, mip and layer count)
- Stores each into ***swapChainImageViews***

## CreateRenderPass
- Uses **swapChainImageFormat** ; **device**
- Define color attachment
- Define subpass and its dependencies
- Creates renderpass Info using information above
- Store into ***renderPass***


## CreateGraphicsPipeline
- Uses **device** ; **renderPass**
- Creates shader modules from our SPIR-V shaders, putting each into a info struct
- Creates dynamic state Info and viewport state Info
- Points vertex to be loaded, and defines type of geometry to be loaded
- Define rasterization information(e.g. polygon mode, linewidth, triangle facing)
- Define multisampling Info
- Define color blend attachment, and color blend state Info
- Store pipeline layout into ***pipelineLayout***
- Generate pipeline info using all of the above + renderPass
- Store into ***graphicsPipeline***
- Destroy shader modules

## CreateFrameBuffer
- Uses **swapChainImageViews** ; **device** ; **renderPass**
- Creates framebuffer Info for each Image View
- Stores into ***swapChainFramebuffers***

## CreateCommandPool
- Creates command pool using graphic queue family information from physical device
- Stores into ***commandPool***

## CreateCommandBuffer
- Uses **commandPool**
- Allocates command buffer.
- Stores into ***commandBuffer***


## CreateSyncObjects
- Creates semaphores for execution synchronization between CPU and GPU



# Loop
For each frame we:
1. Wait for fence
2. Get next image from swapchain
3. Reset command buffer
4. Record new image into command buffer
5. Wait for imageAvailable semaphore
6. Submit command buffer
7. Wait for render Semaphore
8. Present image