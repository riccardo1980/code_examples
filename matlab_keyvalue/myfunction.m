function  myfunction( a, radius, varargin )
% myfunction( a, radius )
%
% OPTIONAL PARAMETERS (key-value pair)
% 'solver' [default: 'explicitLR']
% 'maxit'  [default:            4]
% 'names'  [default: {'pippo', 'pluto', 'paperino'}]
%

% set default value for optionals ( key value pair )
defaultPars.solver = 'explicitLR';
defaultPars.maxit = 4;
defaultPars.names = {'pippo', 'pluto', 'paperino'};

% check for correct number of parameters
narginchk( 2, Inf );

% get parameters 
pars = varOptSet(defaultPars, varargin);

display(a)
display(radius)
display(pars)

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function defaultOpt = varOptSet( defaultOpt, cellin)
% opt = varOptSet(defaultOpt, cellin)
%
% opt           structure containing default values for the caller
% cellin        cell array containing key-value pairs (use varargin{:})
%

options = numel(cellin);

if ( options ~= 0 )
    
    if rem( options, 2 )
        ME = MException('varOptSet:evenVariableArguments',...
            'Options should always go by pair');
        throw(ME);
    end
    
    optFields = cellin(1:2:end);
    inopt = cell2struct( cellin(2:2:end), optFields, 2);
    
    for ii = 1: numel(optFields),
       if isfield( defaultOpt, optFields{ii} ) 
           defaultOpt.(optFields{ii}) = inopt.(optFields{ii});
       else
           ME = MException('varOptSet:unrecognizedKey',...
               [optFields{ii} ' is not a recognized option']);
           throw(ME);
       end
    end

    
end

end
