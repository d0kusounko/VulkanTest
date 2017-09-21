//===========================================================================
//!
//!	@file		VulkanTest.cpp
//!	@brief		VulkanTest
//!
//!	@author 	dO
//!
//===========================================================================
#include <vulkan/vulkan.h>
#include "VulkanTest.h"

#define ERR_EXIT(err_msg, err_class)					\
	do {												\
		MessageBox(NULL, err_msg, err_class, MB_OK);	\
		exit(1);										\
	} while (0)

namespace VulkanTest
{
	struct PhysicalDevice
	{
		VkPhysicalDevice                    Device;
		VkPhysicalDeviceMemoryProperties    MemoryProperty;
		VkPhysicalDeviceProperties          DeviceProperty;
	};

	VkInstance			g_Instance				= nullptr;
	PhysicalDevice*		g_pPhysicalDevices		= nullptr;
	uint32_t			g_PhysicalDeviceCount = 0;

	/*!
	 *	@brief	インスタンス生成.
	 */
	void CreateInstance( const char* appName )
	{
		if( g_Instance ) return;	// インスタンス生成済み.

		VkApplicationInfo appInfo = {};
		appInfo.sType				= VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pNext				= nullptr;
		appInfo.pApplicationName	= appName;
		appInfo.pEngineName			= appName;
		appInfo.apiVersion			= VK_API_VERSION_1_0;

		const char* extensions[] =
		{
			VK_KHR_SURFACE_EXTENSION_NAME,
			VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#if defined( _DEBUG )
			VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
#endif
		};

#if defined( _DEBUG )
		const char* layers[] =
		{
			"VK_LAYER_LUNARG_standard_validation"
		};
#endif

		VkInstanceCreateInfo instanceInfo = {};
		instanceInfo.sType						= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pNext						= nullptr;
		instanceInfo.pApplicationInfo			= &appInfo;
		instanceInfo.enabledExtensionCount		= static_cast< uint32_t >( ArrayLength( extensions ) );
		instanceInfo.ppEnabledExtensionNames	= extensions;
#if defined( _DEBUG )
		instanceInfo.enabledLayerCount			= static_cast< uint32_t >( ArrayLength( layers ) );
		instanceInfo.ppEnabledLayerNames		= layers;
#endif

		VkResult	error;

		error = vkCreateInstance( &instanceInfo, nullptr, &g_Instance );
		if( error == VK_ERROR_INCOMPATIBLE_DRIVER )
		{
			ERR_EXIT( TEXT( "Cannot find a compatible Vulkan installable client driver "
							"(ICD).\n\nPlease look at the Getting Started guide for "
							"additional information.\n" ),
					  TEXT( "vkCreateInstance Failure" ) );
		}
		else if( error == VK_ERROR_EXTENSION_NOT_PRESENT )
		{
			ERR_EXIT( TEXT( "Cannot find a specified extension library"
							".\nMake sure your layers path is set appropriately.\n" ),
					  TEXT( "vkCreateInstance Failure" ) );
		}
		else if( error != VK_SUCCESS )
		{
			ERR_EXIT( TEXT( "vkCreateInstance failed.\n\nDo you have a compatible Vulkan "
							"installable client driver (ICD) installed?\nPlease look at "
							"the Getting Started guide for additional information.\n" ),
					  TEXT( "vkCreateInstance Failure" ) );
		}

		// TODO: デバッグ出力の有効化.
		// PFN_vkCreateDebugReportCallbackEXT
		// PFN_vkDebugReportMessageEXT
		// PFN_vkDestroyDebugReportCallbackEXT
	}

	/*!
	 *	@brief	デバイス生成.
	 */
	void CreateDevice()
	{
		// TODO: マルチGPU対応.

		//--------------------------------------------
		// 物理デバイスの情報を取得.
		//--------------------------------------------
		assert( g_Instance );

		if( g_pPhysicalDevices ) return;

		VkResult	error;
		error = vkEnumeratePhysicalDevices( g_Instance, &g_PhysicalDeviceCount, nullptr );
		assert( error == VK_SUCCESS && g_PhysicalDeviceCount > 0);

		if( g_PhysicalDeviceCount > 0 )
		{
			g_pPhysicalDevices	= new PhysicalDevice[ g_PhysicalDeviceCount ];

			VkPhysicalDevice* physicalDevices	= new VkPhysicalDevice[ g_PhysicalDeviceCount ];
			error = vkEnumeratePhysicalDevices( g_Instance, &g_PhysicalDeviceCount, physicalDevices );
			assert( error == VK_SUCCESS );

			// 各物理デバイスの情報を取得.
			for( uint32_t dev_i = 0; dev_i < g_PhysicalDeviceCount; ++dev_i )
			{
				auto& device = g_pPhysicalDevices[ dev_i ];
				device.Device = physicalDevices[ dev_i ];
				vkGetPhysicalDeviceProperties( physicalDevices[ dev_i ], &device.DeviceProperty );
				vkGetPhysicalDeviceMemoryProperties( physicalDevices[ dev_i ], &device.MemoryProperty );
			}
			delete[] physicalDevices;

		}
		else
		{
			ERR_EXIT(TEXT( "vkEnumeratePhysicalDevices reported zero accessible devices.\n\n"
					 "Do you have a compatible Vulkan installable client driver (ICD) "
					 "installed?\nPlease look at the Getting Started guide for "
					 "additional information.\n" ),
					 TEXT( "vkEnumeratePhysicalDevices Failure" ) );
		}

		//--------------------------------------------
		// デバイスの作成.
		//--------------------------------------------

	}

	/*!
	 *	@brief	インスタンス破棄.
	 */
	void DestroyInstance()
	{
		if( g_Instance == nullptr ) return;
		vkDestroyInstance( g_Instance, nullptr );
	}
}