Source `go-pkg-complete.bash.inc` to get tab completion for the go tool.

Hitting tab after `{go,wgo}` will complete to any of the standard go subcommands.

Hitting tab after `{go,wgo} {install,build,list,get,test,generate,vet,save,vendor}` will complete a go package found in $GOPATH. Or, in the case of wgo, found in the workspace.

License MIT.
