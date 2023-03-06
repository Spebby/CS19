#include "cs19_c_strings.h"
 
namespace cs19 {

    unsigned atoi(const char *str) {
        int result = 0;
        for (int i = 0; str[i] != '\0'; i++) 
            result = result * 10 + str[i] - '0';

        return result;
    }

    const char *strchr(const char *haystack, const char needle) {
        for (int i = 0; haystack[i] != '\0'; i++)
            if (haystack[i] == needle)
                return &haystack[i];

        return nullptr;
    }

    int strcmp(const char *str1, const char *str2) {
        for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
            if (str1[i] != str2[i])
                return str1[i] - str2[i];

        return 0;
    }

    std::size_t strlen(const char *str) {
        int result = 0;
        for (int i = 0; str[i] != '\0'; i++)
            result++;

        return result;
    }

    const char *strpbrk(const char *haystack, const char *char_list) {
        for (int i = 0; haystack[i] != '\0'; i++)
            for (int j = 0; char_list[j] != '\0'; j++)
                if (haystack[i] == char_list[j])
                    return &haystack[i];

        return nullptr;
    }

    const char *strrchr(const char *haystack, const char needle) {
        for (int i = strlen(haystack) - 1; i >= 0; i--)
            if (haystack[i] == needle)
                return &haystack[i];

        return nullptr;
    }

    char *strrev(char *str) {
        int len = strlen(str);
        for (int i = 0; i < len / 2; i++) {
            char temp = str[i];
            str[i] = str[len - i - 1];
            str[len - i - 1] = temp;
        }
        return str;
    }

    const char *strstr(const char *haystack, const char *needle) {
        int len = strlen(needle);
        for (int i = 0; haystack[i] != '\0'; i++)
            if (strcmp(&haystack[i], needle) == 0)
                return &haystack[i];

        return nullptr;
    }

    void strzip(const char *str1, const char *str2, char *output) {
        int i = 0;
        for (int j = 0; str1[j] != '\0' || str2[j] != '\0'; j++) {
            if (str1[j] != '\0')
                output[i++] = str1[j];
            if (str2[j] != '\0')
                output[i++] = str2[j];
        }
        output[i] = '\0';
    }

    char *str_rot13(char *str) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] >= 'A' && str[i] <= 'M')
                str[i] += 13;
            else if (str[i] >= 'N' && str[i] <= 'Z')
                str[i] -= 13;
            else if (str[i] >= 'a' && str[i] <= 'm')
                str[i] += 13;
            else if (str[i] >= 'n' && str[i] <= 'z')
                str[i] -= 13;
        }
        return str;
    }

}