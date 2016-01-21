#include "des.h"

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
using namespace std;

Des::Des(QObject *parent) : QObject(parent)
{

}

bitset<32> Des::f(bitset<32> R, bitset<48> k)
{
    bitset<48> expandR;
    // 第一步：扩展置换，32 -> 48
    for(int i=0; i<48; ++i)
        expandR[47-i] = R[32-E[i]];
    // 第二步：异或
    expandR = expandR ^ k;
    // 第三步：查找S_BOX置换表
    bitset<32> output;
    int x = 0;
    for(int i=0; i<48; i=i+6)
    {
        int row = expandR[47-i]*2 + expandR[47-i-5];
        int col = expandR[47-i-1]*8 + expandR[47-i-2]*4 + expandR[47-i-3]*2
            + expandR[47-i-4];
        int num = S_BOX[i/6][row][col];
        bitset<4> binary(num);
        output[31-x] = binary[3];
        output[31-x-1] = binary[2];
        output[31-x-2] = binary[1];
        output[31-x-3] = binary[0];
        x += 4;
    }
    // 第四步：P-置换，32 -> 32
    bitset<32> tmp = output;
    for(int i=0; i<32; ++i)
        output[31-i] = tmp[32-P[i]];
    return output;
}

/**
 *  对56位密钥的前后部分进行左移
 */
bitset<28> leftShift(bitset<28> k, int shift)
{
    bitset<28> tmp = k;
    for(int i=27; i>=0; --i)
    {
        if(i-shift<0)
            k[i] = tmp[i-shift+28];
        else
            k[i] = tmp[i-shift];
    }
    return k;
}

/**
 *  生成16个48位的子密钥
 */
void Des::generateKeys()
{
    bitset<56> realKey;
    bitset<28> left;
    bitset<28> right;
    bitset<48> compressKey;
    // 去掉奇偶标记位，将64位密钥变成56位
    for (int i=0; i<56; ++i)
        realKey[55-i] = key[64 - PC_1[i]];
    // 生成子密钥，保存在 subKeys[16] 中
    for(int round=0; round<16; ++round)
    {
        // 前28位与后28位
        for(int i=28; i<56; ++i)
            left[i-28] = realKey[i];
        for(int i=0; i<28; ++i)
            right[i] = realKey[i];
        // 左移
        left = leftShift(left, shiftBits[round]);
        right = leftShift(right, shiftBits[round]);
        // 压缩置换，由56位得到48位子密钥
        for(int i=28; i<56; ++i)
            realKey[i] = left[i-28];
        for(int i=0; i<28; ++i)
            realKey[i] = right[i];
        for(int i=0; i<48; ++i)
            compressKey[47-i] = realKey[56 - PC_2[i]];
        subKey[round] = compressKey;
    }
}

/**
 *  工具函数：将char字符数组转为二进制
 */
bitset<64> Des::charToBitset(const char s[8])
{
    bitset<64> bits;
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            bits[i*8+j] = ((s[i]>>j) & 1);
    return bits;
}

/**
 *  DES加密
 */
bitset<64> Des::encrypt(bitset<64>& plain)
{
    bitset<64> cipher;
    bitset<64> currentBits;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newLeft;
    // 第一步：初始置换IP
    for(int i=0; i<64; ++i)
        currentBits[63-i] = plain[64-IP[i]];
    // 第二步：获取 Li 和 Ri
    for(int i=32; i<64; ++i)
        left[i-32] = currentBits[i];
    for(int i=0; i<32; ++i)
        right[i] = currentBits[i];
    // 第三步：共16轮迭代
    for(int round=0; round<16; ++round)
    {
        newLeft = right;
        right = left ^ f(right,subKey[round]);
        left = newLeft;
    }
    // 第四步：合并L16和R16，注意合并为 R16L16
    for(int i=0; i<32; ++i)
        cipher[i] = left[i];
    for(int i=32; i<64; ++i)
        cipher[i] = right[i-32];
    // 第五步：结尾置换IP-1
    currentBits = cipher;
    for(int i=0; i<64; ++i)
        cipher[63-i] = currentBits[64-IP_1[i]];
    // 返回密文
    return cipher;
}

/**
 *  DES解密
 */
bitset<64> Des::decrypt(bitset<64>& cipher)
{
    bitset<64> plain;
    bitset<64> currentBits;
    bitset<32> left;
    bitset<32> right;
    bitset<32> newLeft;
    // 第一步：初始置换IP
    for(int i=0; i<64; ++i)
        currentBits[63-i] = cipher[64-IP[i]];
    // 第二步：获取 Li 和 Ri
    for(int i=32; i<64; ++i)
        left[i-32] = currentBits[i];
    for(int i=0; i<32; ++i)
        right[i] = currentBits[i];
    // 第三步：共16轮迭代（子密钥逆序应用）
    for(int round=0; round<16; ++round)
    {
        newLeft = right;
        right = left ^ f(right,subKey[15-round]);
        left = newLeft;
    }
    // 第四步：合并L16和R16，注意合并为 R16L16
    for(int i=0; i<32; ++i)
        plain[i] = left[i];
    for(int i=32; i<64; ++i)
        plain[i] = right[i-32];
    // 第五步：结尾置换IP-1
    currentBits = plain;
    for(int i=0; i<64; ++i)
        plain[63-i] = currentBits[64-IP_1[i]];
    // 返回明文
    return plain;
}
