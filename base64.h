/*
Copyright (C) 2018 Milosz Kolenderski

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/
#ifndef BASE64_H
#define BASE64_H

///
///Create Base64 decoding table
///
void base64_init(void);

///
///Decode Base64 to raw data
///
//@param in - input data
//@param out - pointer to output buffer
//@param len - length of input data
///
int base64_decode(char * in, char * out, int len);

///
///Encode data using Base64
///
//@param in - input data
//@param out - pointer to output buffer
//@param len - length of input data
///
void base64_encode(char * in, char * out, int len);

#endif
