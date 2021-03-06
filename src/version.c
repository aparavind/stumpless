// SPDX-License-Identifier: Apache-2.0

/*
 * Copyright 2018-2019 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stddef.h>
#include <stumpless/config.h>
#include <stumpless/version.h>
#include "private/error.h"
#include "private/memory.h"
#include "private/strbuilder.h"

struct stumpless_version *
stumpless_get_version( void ) {
  struct stumpless_version *version;

  clear_error(  );

  version = alloc_mem( sizeof( struct stumpless_version ) );
  if( !version ) {
    return NULL;
  }

  version->major = STUMPLESS_MAJOR_VERSION;
  version->minor = STUMPLESS_MINOR_VERSION;
  version->patch = STUMPLESS_PATCH_VERSION;

  return version;
}

char *
stumpless_version_to_string( const struct stumpless_version *version ) {
  struct strbuilder *builder;
  struct strbuilder *aggregate;
  char *version_string;

  clear_error(  );

  if( !version ) {
    raise_argument_empty( "version is NULL" );
    return NULL;
  }

  builder = strbuilder_new(  );

  aggregate = strbuilder_append_int( builder, version->major );
  aggregate = strbuilder_append_char( aggregate, '.' );
  aggregate = strbuilder_append_int( aggregate, version->minor );
  aggregate = strbuilder_append_char( aggregate, '.' );
  aggregate = strbuilder_append_int( aggregate, version->patch );

  version_string = strbuilder_to_string( aggregate );

  strbuilder_destroy( builder );

  return version_string;
}
