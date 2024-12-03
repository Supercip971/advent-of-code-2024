#include "extdlib/base/result.h"
#include "extdlib/io/buf.h"
#include "extdlib/io/file.h"
#include "extdlib/io/funcs.h"
#include "extdlib/parse/nums.h"
#include "extdlib/parse/scan.h"
#include <stdio.h>
#include "extdlib/alloc/global.h"
#include <extdlib/io.h>

#include <extdlib/debug.h>

void init_scanner(Scan *scanner, Buf *buf)
{
    IoFile self = {}; 
    UNWRAP(io_file_view(&self, str$("./finput.txt") ));
    
    log$("file opened: {}", self.embed.fd);

    IoSeeker s = io_file_seeker(&self);

    UNWRAP(s.seek(&self,io_seek_from_end(0)));
    SSize size = UNWRAP(s.seek(&self,io_seek_from_current(0)));
    UNWRAP(s.seek(&self,io_seek_from_start(0)));

    
    IoReader reader = io_file_reader(&self);

    buf_init(buf, size, alloc_global());

    io_copy(reader, buf_writer(buf));

    scan_init(scanner, buf_str(buf));

    io_file_close(&self);
}


typedef struct MulInstruction {
    int a;
    int b;
} MulInstruction;
bool scan_eat_mulInst_impl(Scan* scanner, MulInstruction* result)
{
    if(!scan_skip_word(scanner, str$("mul(")))
    {
        return false;
    }
    unsigned long a = 0;
    unsigned long b = 0;
    if(!scan_next_uint(scanner, &a))
    {
        return false;
    }

    if(!scan_skip(scanner, ','))
    {
        return false;
    }
    
    if(!scan_next_uint(scanner, &b))
    {
        return false;
    }

    if(!scan_skip(scanner, ')'))
    {
        return false;
    }

    result->a = a;
    result->b = b;
    return true;
}
bool scan_skip_mulInst(Scan* scanner, MulInstruction* result)
{
    auto curr = scan_tell(scanner);
 
    bool res = scan_eat_mulInst_impl(scanner, result);

    if(!res)
    {
        scan_seek(scanner, curr);
    }

    return res;
}



typedef struct DoInstruction {
    bool do_ins; // do = true don't = false
} DoInstruction;


bool scan_skip_do_ins(Scan*scanner, DoInstruction* ins)
{
    if(scan_skip_word(scanner, str$("do()")))
    {
        ins->do_ins = true;
        return true;
    }
    else if(scan_skip_word(scanner, str$("don't()")))
    {
        ins->do_ins = false;
        return true;
    }

    return false;
}
int main(void) 
{
    
    Buf data_buf; 
    Scan scanner; 

    init_scanner(&scanner, &data_buf);

    long summed = 0;

    bool do_ins = true;

    while(!scan_ended(&scanner)){

        MulInstruction instruction; 
        DoInstruction do_instruction;
        if(scan_skip_mulInst(&scanner, &instruction))
        {
            if(do_ins)
            {
                summed += instruction.a * instruction.b;

            }
        }
        else if(scan_skip_do_ins(&scanner, &do_instruction))
        {
            do_ins = do_instruction.do_ins;
        }
        else {
            scan_next(&scanner);
        }
    }
    buf_deinit(&data_buf);


    log$("result: {}", summed);



    return 0;
}
