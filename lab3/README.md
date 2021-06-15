

## Requirments

- Linux/macOS.
- GNU make.
- C++11 compliant compiler.

Note that we only support Linux and macOS. Other *nix OS probably does not compile the source. 
Also note, to simplify your target machine setup, we've stripped all CMake related build-system and instead adding some ad-hoc Makefiles such that you can compile the whole project with a simple make command:

```
make
```

## Usage

```
./kvstore2pcsystem [options]

  -h --help [default: (unset)]
      print this message and exit
  -m --mode [default: participant]
      specify the mode of the server. ["coordinator" | "participant"]. Defaulted
       to "participant"
  -a --ip [default: ]
      specify an ip address. Defaulted to 127.0.0.1
  -c --config_path [default: ]
      specify the path to config
  -p --port [default: 0]
      specify a port.
  -P --participant_addrs [default: ]
      specify a list of participant addrs separated by ';'. E.g. "ip1:port1;ip2:p"
      ort2
  -C --coordinator_addr [default: ]
      specify the address of coordinator. E.g., 127.0.0.1:8080
```

