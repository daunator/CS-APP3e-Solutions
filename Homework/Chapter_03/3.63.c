long switch_prob(long x, long n)
{
  long result = x;
  switch (n) {
    case 60:
    case 62:
      result *= 8;
      break;
    case 63:
      result >>= 3;
      break;
    case 64:
      result *= 15;
    case 65:
      result *= result;
    default:
      result += 75;
  }
  return result;
}

