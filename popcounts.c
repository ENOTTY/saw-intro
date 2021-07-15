#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

////////////////// IMPLEMENTATIONS OF POPCOUNT //////////////////////

/* Optimized version from Hacker's Delight book */
int pop_count(uint32_t x) {
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

/* Simple version that iterates through the bits */
int pop_count_ok(uint32_t x) {
	int cnt = 0;
	int len = 32;
	for (int i = 0; i < len; i++) {
		uint32_t mask = 1 << i;
		if (x & mask) cnt++;
	}
	return cnt;
}

/* "specification" of popcount */
int pop_spec(uint32_t x) {
    uint32_t pop = 0;
    uint32_t mask = 1;
    for (int i = 0; i < 32; i++) {
        if (x & mask) { pop++; }
        mask = mask << 1;
    }
    return pop;
}

/* BROKEN - the line adding to `cnt` should use `!!` */
int pop_count_broken1(uint32_t x) {
	int cnt = 0;
	int len = 32;
	for (int i = 0; i < len; i++) {
		uint8_t mask = 1 << i;
		cnt += !(x & mask);
	}
	return cnt;
}

/* BROKEN - random testing won't find this */
int pop_count_broken2(uint32_t x) {
    if (x == 0xDEADBEEF) return 22;
    return pop_count(x);
}

/* BROKEN - mask is incorrect when i is between 8 to 31 because it's declared as an 8-bit integer */
int pop_count_broken3(uint32_t x) {
	int cnt = 0;
	int len = 32;
	for (int i = 0; i < len; i++) {
		uint8_t mask = 1 << i;
		if (x & mask) cnt++;
	}
	return cnt;
}

//////////////////// TESTING POPCOUNT ///////////////////

/* Test pop_count on a few values to make sure it's at least sometimes correct */
bool pop_check() {
    return (pop_count(0x0) == 0) &&
           (pop_count(0x3) == 2) &&
           (pop_count(0xFFFFFFFF) == 32) &&
           (pop_count(0xAAAAAAAA) == 16) &&
           (pop_count(0x55555555) == 16);
}

void random_value_test(int (*fun)(uint32_t), char *name) {
    srand(time(NULL));

    int failures = 0;
    for (int i = 0; i < 100000; i ++) {
        uint32_t x = rand();
        int test = (*fun)(x);
        int check = pop_spec(x);
        if (test != check) {
            printf("Test failure: %s(%u) was %u, != %u\n",
                    name, x, test, check);
            failures++;
        }
    }
    if (failures == 0) {
        printf("Testing %s succeeded!\n", name);
    }
}

//////////////////// VERIFYING POPCOUNTS /////////////////

bool pop_spec_check_pop_count(uint32_t x) {
    return (pop_spec(x) == pop_count(x));
}

bool pop_spec_check_pop_count_ok(uint32_t x) {
    return (pop_spec(x) == pop_count_ok(x));
}

bool pop_spec_check_pop_count_broken1(uint32_t x) {
    return (pop_spec(x) == pop_count_broken1(x));
}

bool pop_spec_check_pop_count_broken2(uint32_t x) {
    return (pop_spec(x) == pop_count_broken2(x));
}

bool pop_spec_check_pop_count_broken3(uint32_t x) {
    return (pop_spec(x) == pop_count_broken3(x));
}

int main(void)
{
	printf("%d\n", pop_count(2415925760));
	printf("%d\n", pop_count_ok(2415925760));
	printf("%d\n", pop_count_broken3(2415925760));
	fputs(pop_check() ? "true\n" : "false\n", stdout);
	return 0;
}
