const exec = require('child_process').exec;

for (let i = 1; i <= 10; i++)
{
    // exec('echo ' + Math.ceil(Math.random() * 100000000) + ' | maker >' + i + '.in', function(error, stdout, stderr){
        // exec('baoli <' + i + '.in >' + i + '.ans', function(error, stdout, stderr){
            exec('game <' + 'game' + i + '.in >' + i + '.out', function(error, stdout, stderr){
                exec('diff ' + 'game' + i + '.out ' + i + '.out', function(error, stdout, stderr){
                    if(stdout.length == 0)
                    {
                        // console.log(stdout);
                        console.log(i + '\033[32m✔ Accepted \033[0m');
                        // exec('rm ' + i + '.ans ' + i + '.in ' + i + '.out');
                    }
                    else
                    {
                        console.log(stdout);
                        console.log(i + '\033[31m✘ Wrong Ans \033[0m');
                    }
                    
                });
            });
        // });
    // });
}