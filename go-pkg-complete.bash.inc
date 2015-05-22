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
    while [[ $1 == -* ]]; do
          shift
    done
    grep -q '^\(install\|build\|list\|get\|test\|generate\|vet\)$' <<< $1 || return


    local cur=${COMP_WORDS[COMP_CWORD]}
    COMPREPLY=( $(compgen -W "$(get_go_pkgs $cur)" -- $cur) )
}

complete -o default -F go_pkg_complete go
complete -o default -F go_pkg_complete wgo
