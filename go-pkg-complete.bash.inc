get_go_pkgs() {
	list_operand=$(dirname $1)
	if [[ "$list_operand" != "." ]]; then
		go list "$list_operand/..." 2> /dev/null | grep "^$1"
	else
		go list "..." 2> /dev/null | grep "^$1"
	fi
}

go_pkg_complete() {
    set -- $COMP_LINE
    shift

    cmd=$0

    while [[ $1 == -* ]]; do
          shift
    done
    if grep -q '^\(install\|build\|list\|get\|test\|generate\|vet\)$' <<< $1; then
        local cur=${COMP_WORDS[COMP_CWORD]}
        COMPREPLY=( $(compgen -W "$(get_go_pkgs $cur)" -- $cur) )
    fi
}

wgo_pkg_complete() {
    GOPATH=$(wgo env GOPATH) go_pkg_complete $@
}

complete -o default -F go_pkg_complete go
complete -o default -F wgo_pkg_complete wgo
