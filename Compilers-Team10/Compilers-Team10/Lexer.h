//#include <ctype.h> 
//#include <stdbool.h> 
//#include <stdio.h> 
//#include <stdlib.h> 
//#include <string.h> 
//#include <string>
//#include "VariadicTable.h"
//#define _CRT_SECURE_NO_WARNINGS 1
//#pragma once
//class Lexer
//{
//
//

//public:
//	bool isDelimiter(char chr) {

//	}
//	bool isOperator(char chr) {
//		return(

//	}
//	bool isBooleanOperator(char chr) {
//		return(

//	}
//	bool isValidID(char* str) {
//		return(
// 
//			str[0] != '0' &&
//			str[0] != '1' &&
//			str[0] != '2' &&
//			str[0] != '3' &&
//			str[0] != '4' &&
//			str[0] != '5' &&
//			str[0] != '6' &&
//			str[0] != '7' &&
//			str[0] != '8' &&
//			str[0] != '9' &&
//			!isDelimiter(str[0]) &&
//			!isOperator(str[0]) &&
//			!isBooleanOperator(str[0]) &&
//			!isKeyword(str)
//			);
//	}
//	bool isKeyword(char* str) {
//		for (int i = 0; i < sizeof(keywords); i++) {
//			if (strcmp(keywords[i], str) == 0) {
//				return true;
//			}
//			else {
//				return false;
//			}
//		}
//	}
//
//	bool isInt(char* str) {
//		if (str == NULL || *str == '\0') {
//			return false;
//		}
//		else {
//			int i = 0;
//			while (isdigit(str[i])) {
//				i++;
//			}
//			return str[i] == '\0';
//		}
//	}
//	bool isFloat(char* str) {
//		if (str == NULL || *str == '\0') {
//			return false;
//		}
//		else {
//			int i = 0;
//			int dots = 0;
//			while (isdigit(str[i]) || str[i] == '.') {
//				if (str[i] == '.') dots++;
//				if (dots > 1) return false;
//				i++;
//			}
//			return str[i] == '\0';
//		}
//	}
//};
//
