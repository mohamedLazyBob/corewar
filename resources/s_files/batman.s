.name       "Batman"
.comment    "This city needs me"

#izjmp %:loop
byte:
	ld %4, r5
loop:
        sti r1, %:live, %1
live:
        live %0
        ld %1, r2
		add r2, r1, r1 
		st r1, :byte
        zjmp %:loop
