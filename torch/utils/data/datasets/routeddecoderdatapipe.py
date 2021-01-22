from torch.utils.data.dataset import IterableDataset
from torch.utils.data.datasets.decoder import (
    Decoder,
    basichandlers as decoder_basichandlers,
    imagehandler as decoder_imagehandler)

from typing import Iterable, Iterator, Union, List, Tuple, Any, Callable
from io import BufferedIOBase

class RoutedDecoderIDP(IterableDataset):
    r""" :class:`RoutedDecoderIDP`.

    Iterable datapipe to decode binary streams from input iterables,
    yield pathname and decoded binary stream in a tuple.
    args:
        datapipe: Iterable datapipe that provides pathname and binary stream in tuples
        decoders: user defined decoders, if None, basic and image decoders will be set as default
        length: a nominal length of the datapipe
    """

    def __init__(
            self,
            datapipe : Iterable[Tuple[str, BufferedIOBase]],
            *,
            decoders : Union[None, List[Callable]] = None,
            length: int = -1):
        super().__init__()
        self.datapipe : Iterable[Tuple[str, BufferedIOBase]] = datapipe
        if decoders:
            self.decoder = Decoder(decoders)
        else:
            self.decoder = Decoder([decoder_basichandlers, decoder_imagehandler('torch')])
        self.length : int = length

    def add_decoder(self, decoder : Callable) -> None:
        self.decoder.add_decoder(decoder)

    def __iter__(self) -> Iterator[Tuple[str, Any]]:
        for data in self.datapipe:
            pathname = data[0]
            result = self.decoder(data)
            yield (pathname, result[pathname])

    def __len__(self):
        if self.length == -1:
            raise NotImplementedError
        return self.length