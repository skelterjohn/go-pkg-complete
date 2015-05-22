get_go_pkgs() {
	[[ $1 ]] && list_operand=$(dirname $1) || list_operand="."
	if [[ "$list_operand" != "." ]]; then
		go list "$list_operand/..." 2> /dev/null | grep "^$1"
	else
		go list "..." 2> /dev/null | grep "^$1"
	fi
}

get_go_cmds() {
    for i in build clean env fix fmt generate get install list run test tool version vet save vendor; do
        [[ $i == $1* ]] && echo $i
    done
}

go_pkg_complete() {
    set -- $COMP_LINE
    shift

    while [[ $1 == -* ]]; do
          shift
    done
    
    local cur=${COMP_WORDS[COMP_CWORD]}
    if grep -q '^\(install\|build\|list\|get\|test\|generate\|vet\|save\|vendor\)$' <<< $1; then
        COMPREPLY=( $(compgen -W "$(get_go_pkgs $cur)" -- $cur) )
        return
    fi

    [[ $2 ]] && return

    COMPREPLY=( $(compgen -W "$(get_go_cmds $cur)" -- $cur) )
}

wgo_pkg_complete() {
    GOPATH=$(wgo env GOPATH) go_pkg_complete $@
}

complete -o default -F go_pkg_complete go
complete -o default -F wgo_pkg_complete wgo
