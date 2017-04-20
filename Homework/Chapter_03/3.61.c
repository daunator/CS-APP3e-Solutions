long cred_alt(long *xp) {
  long x = xp ? *xp : 0;
  return xp ? x : 0;
}

