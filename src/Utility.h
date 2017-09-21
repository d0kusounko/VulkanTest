//===========================================================================
//!
//!	@file		Utility.h
//!	@brief		ユーテリティ.
//!
//!	@author 	dO
//!
//===========================================================================
#pragma once

// 配列の要素数を取得.
template
<
	typename T,
	size_t size
>
size_t ArrayLength( const T (&)[ size ] )
{
	return size;
}