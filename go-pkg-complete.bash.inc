get_go_pkgs_in() {(
    IFS=" "
    gopath="$1"
    word="$2"
    for d in "$gopath"/src/"$word"*; do
        [[ "$d" == *"*" ]] && continue
        [[ -d "$d" ]] || continue
        echo -n "${d/$gopath\/src\/} "
    done
    for d in "$gopath"/src/"$word"/*; do
        [[ "$d" == *"*" ]] && continue
        [[ -d "$d" ]] || continue
        echo -n "${d/$gopath\/src\/}/ "
    done
)}

get_go_pkgs_dup() {(
    word=$1
    IFS=":"
    for g in $GOPATH; do
        get_go_pkgs_in "$g" "$word"
    done
)}


get_go_pkgs() {
    get_go_pkgs_dup $@ | sort | uniq
}

get_go_cmds() {
    for i in build clean env fix fmt generate get install list run test tool version vet save vendor; do
        [[ $i == $1* ]] && echo $i
    done
}

get_go_tools() {
    for i in $(go tool -n); do
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
    elif grep -q '^\(tool\)$' <<< $1; then
        COMPREPLY=( $(compgen -W "$(get_go_tools $cur)" -- $cur) )
        return
    elif grep -q '^\(run\|fmt\)$' <<< $1; then
        compopt -o default
        COMPREPLY=()
        return
    fi

    [[ $2 ]] && return

    COMPREPLY=( $(compgen -W "$(get_go_cmds $cur)" -- $cur) )
}

wgo_pkg_complete() {
    GOPATH=$(wgo env GOPATH) go_pkg_complete $@
}

complete -o nospace -F go_pkg_complete go
complete -o nospace -F wgo_pkg_complete wgo
