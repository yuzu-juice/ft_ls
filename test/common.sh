tmp=$(mktemp -d) || exit 1
trap 'rm -rf "$tmp"' 0
fixture="$tmp/fixture"

mkdir -p "$fixture/subdir"
touch "$fixture/file" "$fixture/.hidden" "$fixture/subdir/nested"

compare() {
  ls "$@" >"$tmp/ls.out" 2>"$tmp/ls.err"
  ls_status=$?
  ./ft_ls "$@" >"$tmp/ft_ls.out" 2>"$tmp/ft_ls.err"
  ft_ls_status=$?

  if [ "$ls_status" != "$ft_ls_status" ]; then
    echo "exit status differs: ls=$ls_status ft_ls=$ft_ls_status" >&2
    exit 1
  fi

  if ! diff -u "$tmp/ls.out" "$tmp/ft_ls.out"; then
    exit 1
  fi

  sed 's/^[^:]*: //' "$tmp/ls.err" >"$tmp/ls.err.out"
  sed 's/^[^:]*: //' "$tmp/ft_ls.err" >"$tmp/ft_ls.err.out"
  if ! diff -u "$tmp/ls.err.out" "$tmp/ft_ls.err.out"; then
    exit 1
  fi
}
