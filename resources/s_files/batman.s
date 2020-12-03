.name       "Batman"
.comment    "This city needs me"

#izjmp %:loop
#and %191365376, :loop, r1
loop:
        sti r1, %:live, %1
live:
        live %0
        ld %1, r2
		ldi r2, r1, r1 
        zjmp %:loop

