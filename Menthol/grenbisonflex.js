const process = require('process');
const { spawn } = require('child_process');
function getargv()
{
    return new Promise(resolve => {
	    resolve(process.argv[0].substring(0,process.argv[0].lastIndexOf('\\')))
  	});
}

function execbisonandflex(e,arr)
{
	const bat = spawn(e, arr);
	return new Promise(resolve => {
	    bat.on('exit', (code) => {
		  resolve(1)
		});
  	});
}

(async ()=>{
	let path = await getargv();
	await execbisonandflex('win_bison.exe',['-d','-v','menthol-bison.y']);
	await execbisonandflex('win_flex.exe',['--nounistd','menthol-Flex.l']);
})();
