package manifest

type Manifest struct {
	Label  string
	Cbo    uint32
	Cre    uint32
	Secret []byte
}
