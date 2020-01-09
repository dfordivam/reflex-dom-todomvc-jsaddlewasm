{-# LANGUAGE ForeignFunctionInterface #-}

module AppMain where

import qualified Reflex.TodoMVC
import Language.Javascript.JSaddle.Wasm

import Foreign.Marshal.Alloc
import Foreign.StablePtr
import Data.Int (Int64)
import Foreign.C.String

foreign export ccall hsAppInit :: IO (StablePtr HsEnv)

hsAppInit :: IO (StablePtr HsEnv)
hsAppInit = jsaddleInit 0 Reflex.TodoMVC.main

foreign export ccall hsAppExecStep :: StablePtr HsEnv -> CString -> Int -> IO Int64

hsAppExecStep :: StablePtr HsEnv -> CString -> Int -> IO Int64
hsAppExecStep = jsaddleExecStep

foreign export ccall hsMalloc :: Int -> IO CString

hsMalloc :: Int -> IO CString
hsMalloc = mallocBytes
