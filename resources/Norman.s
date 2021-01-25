.name "Norman" # I love peace
.comment "The promised Neverland is so good!" # Check it out

sti r1, %12, %1				# 7 bytes
xor r1, r1, r1				# 5
live %12					# 5
zjmp %-5					# 3

# 0b 68 01 00 0c 00 01 08 54 01 01 01 01 00 00 00 0c 09 ff fb