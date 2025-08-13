const path = require('path')
const tasks = require('../.vscode/task.json')
const { exec } = require('child_process')
const objPath = require('./filePaths') 


function openApp(){
    const appPath = path.join( __dirname, '../build/app.exe')
    exec( `start ${appPath}` )
}

function getBuildCommand(){
    
    const compileCmd = tasks.tasks[0].args

    compileCmd.unshift( objectToPaths( objPath ) )

    compileCmd.unshift("g++")
    
    return compileCmd.join(' ')

}

function objectToPaths(obj, folderName = "") {
    let paths = [];

    if (obj.files && Array.isArray(obj.files)) {
        for (let file of obj.files) {
            let caminho = folderName ? `${folderName}/${file}` : file;
            paths.push(caminho);
        }
    }

    if (obj.folders && typeof obj.folders === "object") {
        for (let folder in obj.folders) {
            let prefix = folderName ? `${folderName}/${folder}` : folder;
            paths.push(
                objectToPaths(obj.folders[folder], prefix)
            );
        }
    }

    return paths.flat().join(" ")
}


function build( command, callback ){

    exec( command, (error, stdout, stderr) => {

        if (error) {
            console.error(`Erro na compilação: ${error.message}`);
            return;
        }

        if (stderr) console.error(`Avisos/erros do compilador:\n${stderr}`);
        
        console.log(`out> ${stdout}\n`);
        
        callback( stdout )

    });

}

module.exports = {
    build, getBuildCommand, openApp, objectToPaths
}