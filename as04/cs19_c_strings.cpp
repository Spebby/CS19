#include "cs19_c_strings.h"

namespace cs19 {

    unsigned atoi(const char *str) {
        int result = 0;
        for (; *str; str++)
            result = result * 10 + *str - '0';

        return result;
    }

    const char *strchr(const char *haystack, const char needle) {
        for (; *haystack; haystack++)
            if (*haystack == needle)
                return haystack;

        return nullptr;
    }

    int strcmp(const char *str1, const char *str2) {
        for (; *str1 || *str2; str1++, str2++)
            if (*str1 != *str2)
                return *str1 - *str2;

        return 0;
    }

    std::size_t strlen(const char *str) {
        int result = 0;
        while (*str++)
            result++;
        // `for (; *str; str++) {}` is equivalent to above

        return result;
    }

    const char *strpbrk(const char *haystack, const char *char_list) {
        for (; *haystack; haystack++)
            for (const char *needle = char_list; *needle; needle++)
                if (*haystack == *needle)
                    return haystack;

        return nullptr;  // no match
    }

    const char *strrchr(const char *haystack, const char needle) {
        for (int i = strlen(haystack) - 1; i >= 0; i--)
            if (haystack[i] == needle)
                return haystack + i;  // equivalent to &haystack[i]

        return nullptr;
    }

    char *strrev(char *str) {
        int len = strlen(str);
        for (int i = 0; i < len * .5f; i++) {
            char temp = str[i];
            str[i] = str[len - i - 1];
            str[len - i - 1] = temp;
        }
        return str;
    }

    const char *strstr(const char *haystack, const char *needle) {
        for (; *haystack; haystack++)
            if (*haystack == *needle) {
                const char *haystack_copy = haystack;
                const char *needle_copy = needle;
                for (; *haystack_copy && *needle_copy; haystack_copy++, needle_copy++)
                    if (*haystack_copy != *needle_copy)
                        break;
                if (!*needle_copy)
                    return haystack;
            }

        return nullptr;
    }

    void strzip(const char *str1, const char *str2, char *output) {
        while (*str1 || *str2) {
            if (*str1) {
                *output = *str1;
                output++;
                str1++;
            }
            if (*str2) {
                *output = *str2;
                output++;
                str2++;
            }
        }

        *output = '\0';  // terminate the string
    }

    char *str_rot13(char *str) {
        for (; *str; str++) {
            if (*str >= 'A' && *str <= 'M')
                *str += 13;
            else if (*str >= 'N' && *str <= 'Z')
                *str -= 13;
            else if (*str >= 'a' && *str <= 'm')
                *str += 13;
            else if (*str >= 'n' && *str <= 'z')
                *str -= 13;
        }
        return str;
    }
    // this is gross, but i don't care!!!!

}  // namespace cs19