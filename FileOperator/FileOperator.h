// EasyCpp - FileOperator : A Lightweight File Operation Library
// Copyright (C) 2025  C14147
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

/** @file EaspCpp/FileOperator/FileOperator.h
 *  A lightweight file manipulation library dedicated to simplifying the
 *  tedious file manipulation code and improving development efficiency.
 */

#pragma once
#define _EASYCPP_FILEOPERATOR_VERSION "1.0.0"

#ifdef EASYCPP_ALLOW_BIG_FILE
#define _FILE_OFFSET_BITS 64
#endif //_EASYCPP_ALLOW_BIG_FILE_

#ifndef FMT_HEADER_ONLY
#define FMT_HEADER_ONLY
#endif //FMT_HEADER_ONLY

#define WRITE "w"
#define READ "r"
#define APPEND "a"
#define WRITE_E "w+"
#define READ_E "r+"
#define APPEND_E "a+"
#define PERMISSION_READ "readable"
#define PERMISSION_WRITE "writable"
#define PERMISSION_EXECUTE "executable"
#define FILE_NOT_PERMISSION "have permission"

#define F_OK 0 /* Check for file existence */
#define X_OK 1 /* Check for execute permission. */
#define W_OK 2 /* Check for write permission */
#define R_OK 4 /* Check for read permission */

#include <cstdio>
#include <exception>
#include <cstring>
#include <io.h>
#include <process.h>
#include <cstdlib>

namespace easycpp {
	
	bool is_exist(const char * filename) {
		return access(filename, F_OK) == 0;
	}
	
	bool is_readable(const char * filename) {
		return access(filename, R_OK) == 0;
	}
	
	bool is_writable(const char * filename) {
		return access(filename, W_OK) == 0;
	}
	
	bool is_executable(const char * filename) {
		return access(filename, X_OK) == 0;
	}
	
	bool check_permission(const char * filename) {
		return access(filename, R_OK | W_OK) == 0;
	}
	
	class FileNotExistError: public std::exception {
	public:
		char message[256];
		FileNotExistError(char * msg) {
			sprintf(message, "The file '%s' does not exist.", msg);
		}
		const char * what() const throw() {
			return message;
		}
	};
	
	class FilePermissionError: public std::exception {
	public:
		char message[256];
		FilePermissionError(char * msg, const char * permission = FILE_NOT_PERMISSION) {
			sprintf(message, "The file '%s' does not %s.", msg, permission);
		}
		const char * what() const throw() {
			return message;
		}
	};
	
	class FileWriteError: public std::exception {
	public:
		char message[256];
		FileWriteError(char * msg) {
			sprintf(message, "The length of data written to the file '%s' does not match the expected length.", msg);
		}
		const char * what() const throw() {
			return message;
		}
	};
	
	class FileUnknownError: public std::exception {
	public:
		char message[256];
		FileUnknownError(char * msg) {
			sprintf(message, "Can't open the file with fopen_s function:'%s'", msg);
		}
		const char * what() const throw() {
			return message;
		}
	};
	
	class File {
	public:
		FILE * file;
		char * filename;
		File(FILE * file, const char * filename) {
			this->file = file;
			this->filename = new char[strlen(filename) + 1];
			strcpy(this->filename, filename);
		}
		~File() {
			if (file) fclose(file);
			delete[] filename;
		}
		int close() {
			return fclose(file);
		}
		char* read_() {
			fseek(file, 0, SEEK_END);
			int file_size = ftell(file);
			char* tmp = (char*) malloc((file_size + 1) * sizeof(char));
			if (tmp == nullptr) throw std::bad_alloc();
			memset(tmp, '\0', (file_size + 1) * sizeof(char));
			fseek(file, 0, SEEK_SET);
			fread(tmp, sizeof(char), file_size, file);
			return tmp;
		}
		int write(const char * data) {
			int data_size = strlen(data) * sizeof(char);
			int write_size = (int) fwrite(data, sizeof(char), data_size, file);
			if (write_size != data_size) throw FileWriteError(const_cast<char*>(filename));
			return write_size;
		}
	};
	
	File * open(const char * filename, const char * method) {
		if(strcmp(method, READ) == 0 || strcmp(method, READ_E) == 0){
			if (!is_exist(filename)) 
				throw FileNotExistError(const_cast<char*>(filename));
			if (!check_permission(filename)) 
				throw FilePermissionError(const_cast<char*>(filename));
		}
		FILE * _file;
		errno_t _err = fopen_s(& _file, filename, method);
		if (_err != 0) throw FileUnknownError(const_cast<char*>(filename));
		File* _rtn = new File(_file, filename);
		return _rtn;
	}
}
