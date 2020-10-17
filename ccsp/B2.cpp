#include <bits/stdc++.h>
using namespace std;
struct data{
  string name;
  string val;
  int type;
  data() {type = 1;}
  data(string &namev) {
    name = namev;
    type = 1;
  }
  data(string &namev, int typev) {
    name = namev;
    type = typev;
  }
  bool operator < (const data &c) const {
    if (type == c.type)
      return name < c.name;
    return type > c.type;
  }
  bool operator == (const data &c) const {
    return name == c.name;
  }
};
char buffer[10000005];
struct cmp{
  bool operator() (const data* a, const data *b) const {
    if (a->type == b->type)
      return a->name < b->name;
    return a->type > b->type;
  }
};
struct commites{
  set<data*, cmp> file;
  commites *fa, *mf;
  string name;
  commites() {
    fa = mf = NULL;
  }
  commites(string &namev) {
    fa = mf = NULL;
    name = namev;
  }
}*HEAD, *uncom;
// set<data*, cmp> file;
struct cmp2{
  bool operator() (const commites* a, const commites *b) const {
    return a->name < b->name;
  }
};
set<commites*, cmp2> commitesset;
void dfsls(commites *ret, set<data*, cmp> &bufset) {
  if (ret == NULL) return;
  dfsls(ret->fa, bufset);
  for (auto x : ret->file) {
    if (x->type == 1) {
      bufset.erase(x);
      // bufset.erase(new data(x->name, -x->type));
      bufset.insert(x);
    } else {
      bufset.erase(new data(x->name, -x->type));
    }
  }
}
data *findname(string filename, int &info) {
  data *tmp = new data(filename);
  set<data*, cmp> bufset;
  dfsls(HEAD, bufset);
  if (uncom != NULL) {
    if (uncom->file.count(tmp))
      return *(uncom->file.find(tmp));
  }
  if (uncom != NULL) {
    for (auto x : uncom->file) {
      if (x->type == 1) {
        // bufset.erase(x);
        // bufset.insert(x);
      } else {
        bufset.erase(new data(x->name, -x->type));
      }
    }
  }
  if (bufset.size() > 0) {
    if (bufset.count(tmp)) {
      info = 1;
      return (*bufset.find(tmp));
      // uncom->file.insert(p);
      // return p;
    }
  }
  return NULL;
}
commites *findnameset(string filename) {
  data *tmp = new data(filename);
  set<data*, cmp> bufset;
  dfsls(HEAD, bufset);
  if (uncom != NULL) {
    if (uncom->file.count(tmp))
      return uncom;
  }
  if (uncom != NULL) {
    for (auto x : uncom->file) {
      if (x->type == 1) {
        // bufset.erase(x);
        // bufset.insert(x);
      } else {
        bufset.erase(new data(x->name, -x->type));
      }
    }
  }
  if (bufset.size() > 0) {
    if (bufset.count(tmp)) {
      return HEAD;
      // uncom->file.insert(p);
      // return p;
    }
  }
  return NULL;
}
void ls() {
  set<data*, cmp> bufset;
  dfsls(HEAD, bufset);
  if (uncom != NULL) {
    for (auto x : uncom->file) {
      if (x->type == 1) {
        bufset.erase(x);
        bufset.insert(x);
      } else {
        bufset.erase(new data(x->name, -x->type));
      }
    }
  }
  if (bufset.size() != 0) {
    auto x = bufset.end();
    x--;
    printf ("%u %s %s\n", bufset.size(), (*bufset.begin())->name.c_str(), (*x)->name.c_str());
  }
  else {
    printf ("0\n");
  }
}
void write() {
  string filename;
  int offset, len;
  if (uncom == NULL) {
    uncom = new commites;
  }
  scanf ("%s%d%d", buffer, &offset, &len);
  filename = string(buffer);
  int info = 0;
  data *p = findname(filename, info);
  if (p == NULL) {
    data *tmp = new data(filename, -1);
    if (uncom->file.count(tmp)) {
      uncom->file.erase(tmp);
    }
    p = new data(filename);
    uncom->file.insert(p);
  }
  if (info == 1) {
    p = new data(*p);
    uncom->file.insert(p);
  }
  if (p->val.size() < offset + len) {
    p->val.resize(offset + len + 1);
  }
  getchar();
  fgets(buffer, len + 1, stdin);
  p->val.replace(offset + 1, offset + len + 1, buffer);
  // cerr << p->val.size();
  // cout << p->val;
  // cin >> filename >> offset >> len;
}
void read() {
  string filename;
  int offset, len;
  scanf ("%s%d%d", buffer, &offset, &len);
  filename = string(buffer);
  int info = 0;
  data *p = findname(filename, info);
  if (p == NULL) {
    for (int i = 1; i <= len; i++) {
      printf (".");
    }
    printf ("\n");
    return;
  }
  if (offset > p->val.size()) {
    for (int i = 1; i <= len; i++) {
      printf (".");
    }
    printf ("\n");
    return;
  }
  int lastlen = 0;
  int str_len = p->val.size();
  for (int i = 1; i <= len; i++) {
    if (i + offset >= str_len) {
      lastlen = len - i + 1;
      break;
    }
    printf ("%c", (p->val[i + offset] == 0) ? '.' : p->val[i + offset]);
  }
  for (int i = 1; i <= lastlen; i++) {
    printf (".");
  }
  printf ("\n");
}
void unlink() {
  string filename;
  scanf ("%s", buffer);
  filename = string(buffer);
  commites *p = findnameset(filename);
  if (p == NULL) return;
  else {
    if (p == uncom) {
      p->file.erase(new data(filename));
      p->file.insert(new data(filename, -1));
    } else {
      if (uncom == NULL) uncom = new commites();
      uncom->file.insert(new data(filename, -1));
    }
  }
}
commites *findcmtname(string cmtname) {
  commites *tmp = new commites(cmtname);
  if (!commitesset.count(tmp))
    return NULL;
  else
    return *(commitesset.find(tmp));
}
void commit() {
  string cmtname;
  scanf ("%s", buffer);
  cmtname = string(buffer);
  if (uncom == NULL) return;
  if (findcmtname(cmtname)) return;
  uncom->name = cmtname;
  uncom->fa = HEAD;
  HEAD = uncom;
  commitesset.insert(uncom);
  uncom = NULL;
}
void checkout() {
  string cmtname;
  scanf ("%s", buffer);
  cmtname = string(buffer);
  if (uncom != NULL) return;
  commites *ret = findcmtname(cmtname);
  if (ret == NULL) return;
  HEAD = ret; 
}
void merge() {

}
char op[15];
int main() {
  int n;
  // ios::sync_with_stdio(false);
  scanf ("%d", &n);
  // cin >> n;
  while (n--) {
    scanf ("%s", op);
    // cin >> op;
    if (op[0] == 'r') {
      read();
    }
    if (op[0] == 'w') {
      write();
    }
    if (op[0] == 'u') {
      unlink();
    }
    if (op[0] == 'l') {
      ls();
    }
    if (op[1] == 'o') {
      commit();
    }
    if (op[1] == 'h') {
      checkout();
    }
    if (op[0] == 'm') {
      merge();
    }
  }
}