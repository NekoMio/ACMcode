void gauss() {
  int im, num = 1;
  for (int k = 1; k <= n; k++, num++) {
    im = k;
    for (int i = k + 1; i <= n; i++) {
      if (fabs(a[i][k]) > fabs(a[im][k])) i = im;
    }
    if (im != k) {
      for (int i = k; i <= n + 1; i++) swap(a[num][i], a[im][i]);
    }
    if (!a[num][k]) {
      num--;
      continue;
    }
    for (int i = num + 1; i <= n; i++) {
      if (!a[num][k]) continue;
      long double t = a[i][k] / a[num][k];
      for (int j = k; j <= n + 1; j++) {
        a[i][j] -= t * a[k][j];
      }
    }
  }
  for (int i = n; i >= 1; i--) {
    for (int j = n; j >= i + 1; j--) {
      a[i][n + 1] -= a[i][j] * x[j];
    }
    x[i] = a[i][n + 1] / a[i][i];
    sum += x[i];
  }
}