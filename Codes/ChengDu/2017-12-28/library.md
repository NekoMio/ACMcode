# 3 加帕里图书馆(library)
### 3.1 Description
博士经常阅读图书馆里的书籍。有一天，她在书中看到了一个长长的只由小写字母组成的字符串S。博士发现这个串有很多子序列都是回文串，非常优美，于是便列出了这个串的所有非空回文子序列。可是，博士忽然发现，她列出了很多相同的回文串。博士想知道，如果她只想把每种重复的串保留一个，一共需要从她的列表中移除多少回文串？


**子序列** S的一个子序列可以用一个数组p表示，构成的子序列为Sp1 Sp2 ... Spm，其中m为该子序列的长度。满足0 < p1 < p2 < ... < pm <= |S|。

### 3.2 Input Format

一行一个非空字符串S。

### 3.3 Output Format
输出一行一个整数，表示博士一共需要移除多少重复的回文串。由于答案可能很大，请对109 + 7 取模。
### 3.4 Sample 1
#### 3.4.1 Input
```
bccb
```
#### 3.4.2 Output
```
3
```
### 3.5 Sample 2
#### 3.5.1 Input
```
abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba
```
#### 3.5.2 Output
```
679266098
```

### 3.6 Constraints
对于30% 的数据，|S| <= 20。  
对于60% 的数据，|S| <= 100。  
对于100% 的数据，1 <= |S| <= 2000，S 只会包含小写字母。  

### 3.7 Hint
对于第一组样例，非空子序列一共有：  
{b,c,c,b,bc,bc,bb,cc,cb,cb,bcc,bcb,bcb,ccb,bccb}。  
其中回文子序列有：  
{b,c,c,b,bb,cc,bcb,bcb,bccb}。  
需要删去3 个重复的回文子序列。  