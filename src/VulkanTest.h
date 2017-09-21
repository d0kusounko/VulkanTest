//===========================================================================
//!
//!	@file		VulkanTest.h
//!	@brief		VulkanTest
//!
//!	@author 	dO
//!
//===========================================================================
#pragma once

namespace VulkanTest
{
	//! インスタンス生成.
	void CreateInstance( const char* appName );

	// デバイス生成.
	void CreateDevice();

	//! インスタンス破棄.
	void DestroyInstance();
}