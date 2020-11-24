.name       "Batman"
.comment    "This city needs me"

#izjmp %:loop
and %03, %:live, r1
loop:
        sti r1, %:live, %1
live:
        live %0
        ld %0, r2
        zjmp %:loop

