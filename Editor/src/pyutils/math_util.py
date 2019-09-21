import hashlib

## return types = int, str (hex string)
def md5Hash(string, return_type="long"):
    assert return_type in ["long","str"]
    h = hashlib.md5(string.encode())
    if return_type == "str":
        return h.hexdigest()
    elif return_type == "long":
        SIGNED_LONG_LONG_MAX = 9223372036854775807
        return eval("0x"+h.hexdigest())% SIGNED_LONG_LONG_MAX
